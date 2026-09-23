---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-23 09:06:35 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 10 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 971 |
| Sample Rate | 16.18/sec |
| Health Score | 1011% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 47-51 cores)</summary>

```
1790168522 49
1790168527 49
1790168532 49
1790168537 49
1790168543 49
1790168548 49
1790168553 47
1790168558 47
1790168563 47
1790168568 49
1790168573 49
1790168578 49
1790168583 49
1790168588 49
1790168593 49
1790168598 51
1790168603 51
1790168608 51
1790168613 51
1790168618 51
```
</details>

---

