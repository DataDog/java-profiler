---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-05 15:44:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 10 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 764 |
| Sample Rate | 12.73/sec |
| Health Score | 796% |
| Threads | 11 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (4 unique values: 74-82 cores)</summary>

```
1772743010 76
1772743015 74
1772743020 74
1772743025 74
1772743030 78
1772743035 78
1772743040 82
1772743045 82
1772743050 82
1772743055 82
1772743060 82
1772743065 82
1772743070 82
1772743075 82
1772743080 82
1772743085 82
1772743090 82
1772743095 78
1772743100 78
1772743105 78
```
</details>

---

