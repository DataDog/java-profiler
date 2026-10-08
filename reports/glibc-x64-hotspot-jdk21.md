---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-08 01:03:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (4 unique values: 51-84 cores)</summary>

```
1791435497 53
1791435502 53
1791435507 53
1791435512 55
1791435517 55
1791435522 51
1791435527 51
1791435532 51
1791435537 51
1791435542 51
1791435547 51
1791435552 51
1791435557 51
1791435562 51
1791435567 51
1791435572 51
1791435577 84
1791435582 84
1791435587 84
1791435592 84
```
</details>

---

