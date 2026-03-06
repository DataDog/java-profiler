---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-06 04:35:41 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 10 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 13 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 52-64 cores)</summary>

```
1772789486 52
1772789491 52
1772789496 52
1772789501 52
1772789506 52
1772789511 52
1772789516 52
1772789521 64
1772789526 64
1772789531 64
1772789536 64
1772789541 64
1772789546 64
1772789551 64
1772789556 64
1772789561 64
1772789566 64
1772789571 64
1772789576 64
1772789581 64
```
</details>

---

