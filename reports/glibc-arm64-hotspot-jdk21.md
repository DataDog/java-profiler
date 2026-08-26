---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-26 07:12:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 13 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1787742477 40
1787742482 40
1787742487 40
1787742492 40
1787742497 40
1787742502 40
1787742507 40
1787742512 40
1787742517 40
1787742522 40
1787742527 40
1787742533 40
1787742538 40
1787742543 40
1787742548 40
1787742553 40
1787742558 40
1787742563 40
1787742568 40
1787742573 40
```
</details>

---

