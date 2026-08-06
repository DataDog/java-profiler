---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-06 09:00:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 861 |
| Sample Rate | 14.35/sec |
| Health Score | 897% |
| Threads | 10 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (4 unique values: 70-76 cores)</summary>

```
1786020947 70
1786020952 70
1786020957 70
1786020962 72
1786020967 72
1786020972 72
1786020977 72
1786020982 72
1786020987 72
1786020992 72
1786020997 72
1786021002 74
1786021007 74
1786021012 74
1786021017 74
1786021022 74
1786021027 76
1786021032 76
1786021037 76
1786021042 76
```
</details>

---

