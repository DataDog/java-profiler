---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-26 09:38:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 978 |
| Sample Rate | 16.30/sec |
| Health Score | 1019% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 77-94 cores)</summary>

```
1793021596 79
1793021601 79
1793021606 79
1793021611 79
1793021616 79
1793021621 79
1793021626 79
1793021631 79
1793021636 79
1793021641 77
1793021646 77
1793021651 77
1793021656 77
1793021661 77
1793021666 77
1793021671 77
1793021676 77
1793021681 77
1793021686 77
1793021691 77
```
</details>

---

