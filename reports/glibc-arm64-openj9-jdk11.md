---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-12 05:55:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 934 |
| Sample Rate | 15.57/sec |
| Health Score | 973% |
| Threads | 9 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1791798701 40
1791798706 40
1791798711 40
1791798716 40
1791798721 40
1791798726 40
1791798731 40
1791798736 40
1791798741 40
1791798746 40
1791798751 40
1791798756 40
1791798761 40
1791798766 40
1791798771 40
1791798776 40
1791798781 40
1791798786 40
1791798791 40
1791798796 40
```
</details>

---

