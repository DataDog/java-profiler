---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 00:06:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 280 |
| Sample Rate | 4.67/sec |
| Health Score | 292% |
| Threads | 10 |
| Allocations | 187 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 14 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (3 unique values: 33-43 cores)</summary>

```
1794978133 38
1794978138 38
1794978143 38
1794978148 38
1794978153 33
1794978158 33
1794978163 33
1794978168 33
1794978173 33
1794978178 33
1794978183 33
1794978188 33
1794978193 33
1794978198 38
1794978203 38
1794978208 38
1794978213 38
1794978218 38
1794978223 38
1794978228 43
```
</details>

---

