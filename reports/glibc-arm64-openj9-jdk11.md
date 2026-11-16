---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 07:24:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 13 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (3 unique values: 46-51 cores)</summary>

```
1794831562 48
1794831567 48
1794831572 48
1794831577 48
1794831582 48
1794831587 48
1794831592 46
1794831597 46
1794831602 46
1794831607 46
1794831612 46
1794831617 46
1794831622 46
1794831627 46
1794831632 46
1794831637 46
1794831642 46
1794831647 46
1794831652 46
1794831657 46
```
</details>

---

