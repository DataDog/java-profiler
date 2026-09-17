---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 18:03:56 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 230 |
| Sample Rate | 3.83/sec |
| Health Score | 239% |
| Threads | 11 |
| Allocations | 129 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 25-30 cores)</summary>

```
1789682140 25
1789682145 25
1789682150 25
1789682155 25
1789682160 25
1789682165 25
1789682170 25
1789682175 25
1789682180 25
1789682185 25
1789682190 25
1789682195 25
1789682201 25
1789682206 25
1789682211 25
1789682216 25
1789682221 25
1789682226 25
1789682231 25
1789682236 25
```
</details>

---

