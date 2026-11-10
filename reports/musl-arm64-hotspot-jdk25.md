---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 11:01:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 10 |
| Allocations | 556 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1794326116 28
1794326121 28
1794326126 28
1794326131 28
1794326136 28
1794326141 28
1794326146 28
1794326151 28
1794326156 28
1794326161 28
1794326166 28
1794326171 23
1794326176 23
1794326181 23
1794326186 23
1794326191 23
1794326196 23
1794326201 23
1794326206 23
1794326211 23
```
</details>

---

