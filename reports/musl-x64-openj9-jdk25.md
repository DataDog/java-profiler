---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 10:36:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 402 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 9 |
| Allocations | 422 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 11 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1795620711 64
1795620716 64
1795620721 64
1795620726 64
1795620731 64
1795620736 62
1795620742 62
1795620747 62
1795620752 62
1795620757 62
1795620762 62
1795620767 62
1795620772 62
1795620777 62
1795620782 62
1795620787 62
1795620792 62
1795620797 62
1795620802 62
1795620807 62
```
</details>

---

