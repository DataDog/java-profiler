---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-12 10:15:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 10 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 12.77/sec |
| Health Score | 798% |
| Threads | 13 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 50-55 cores)</summary>

```
1770908995 55
1770909000 55
1770909005 55
1770909010 55
1770909015 55
1770909020 50
1770909025 50
1770909030 50
1770909035 50
1770909040 50
1770909045 50
1770909050 50
1770909055 50
1770909060 50
1770909065 50
1770909070 50
1770909075 50
1770909080 50
1770909085 50
1770909090 50
```
</details>

---

