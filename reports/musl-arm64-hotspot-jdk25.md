---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-05 11:49:03 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 8 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 12 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (4 unique values: 43-46 cores)</summary>

```
1791215055 45
1791215060 43
1791215065 43
1791215070 43
1791215075 43
1791215080 44
1791215085 44
1791215090 44
1791215095 44
1791215100 44
1791215105 44
1791215110 44
1791215115 44
1791215120 44
1791215125 44
1791215130 44
1791215135 44
1791215140 46
1791215145 46
1791215150 46
```
</details>

---

