---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-29 04:21:13 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 905 |
| Sample Rate | 15.08/sec |
| Health Score | 942% |
| Threads | 11 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 80-88 cores)</summary>

```
1790669747 88
1790669752 88
1790669757 88
1790669762 88
1790669767 88
1790669772 88
1790669777 88
1790669782 88
1790669787 88
1790669792 80
1790669797 80
1790669802 80
1790669807 80
1790669812 80
1790669817 80
1790669822 80
1790669827 80
1790669832 80
1790669837 80
1790669842 80
```
</details>

---

