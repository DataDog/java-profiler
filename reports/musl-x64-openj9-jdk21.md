---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-16 07:09:32 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (5 unique values: 74-84 cores)</summary>

```
1792148621 76
1792148626 76
1792148631 76
1792148636 76
1792148641 76
1792148646 76
1792148651 74
1792148656 74
1792148661 74
1792148666 74
1792148671 74
1792148676 74
1792148681 78
1792148686 78
1792148691 78
1792148696 84
1792148701 84
1792148706 84
1792148711 84
1792148716 84
```
</details>

---

