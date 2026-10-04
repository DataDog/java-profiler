---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-04 01:00:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 876 |
| Sample Rate | 14.60/sec |
| Health Score | 912% |
| Threads | 12 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (5 unique values: 69-81 cores)</summary>

```
1791089701 76
1791089706 76
1791089711 76
1791089716 76
1791089721 76
1791089726 81
1791089731 81
1791089736 81
1791089741 81
1791089746 81
1791089751 81
1791089756 73
1791089761 73
1791089766 71
1791089771 71
1791089776 71
1791089781 71
1791089786 71
1791089791 71
1791089796 69
```
</details>

---

