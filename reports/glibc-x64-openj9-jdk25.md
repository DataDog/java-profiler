---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-27 13:58:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (3 unique values: 85-89 cores)</summary>

```
1793123701 87
1793123706 87
1793123711 87
1793123716 87
1793123721 87
1793123726 87
1793123731 87
1793123736 85
1793123741 85
1793123746 85
1793123751 85
1793123756 89
1793123761 89
1793123766 89
1793123771 89
1793123776 89
1793123781 89
1793123786 89
1793123791 89
1793123796 89
```
</details>

---

