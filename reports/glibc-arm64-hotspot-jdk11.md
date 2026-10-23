---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-23 10:30:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 13 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (5 unique values: 43-48 cores)</summary>

```
1792765522 44
1792765527 44
1792765532 44
1792765537 44
1792765542 44
1792765547 44
1792765552 44
1792765557 44
1792765562 44
1792765567 44
1792765572 44
1792765577 44
1792765582 44
1792765587 44
1792765592 43
1792765597 43
1792765602 43
1792765607 45
1792765612 45
1792765617 46
```
</details>

---

