---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-09 10:23:32 EDT

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 10 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (4 unique values: 84-90 cores)</summary>

```
1791555444 90
1791555449 90
1791555454 90
1791555459 90
1791555464 90
1791555469 90
1791555474 90
1791555479 90
1791555484 90
1791555489 86
1791555494 86
1791555499 86
1791555504 86
1791555509 86
1791555514 88
1791555519 88
1791555524 88
1791555529 88
1791555534 86
1791555539 86
```
</details>

---

