---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 03:56:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792655555 43
1792655560 43
1792655565 43
1792655570 48
1792655575 48
1792655580 48
1792655585 48
1792655590 48
1792655595 48
1792655600 48
1792655605 48
1792655610 48
1792655615 48
1792655620 48
1792655625 48
1792655630 48
1792655635 48
1792655640 48
1792655645 48
1792655650 48
```
</details>

---

