---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-02 12:03:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 11 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (3 unique values: 83-93 cores)</summary>

```
1790956743 83
1790956748 83
1790956753 83
1790956758 83
1790956763 83
1790956768 83
1790956773 83
1790956778 83
1790956783 88
1790956788 88
1790956793 88
1790956798 88
1790956803 93
1790956808 93
1790956813 93
1790956818 93
1790956823 93
1790956828 93
1790956833 93
1790956838 93
```
</details>

---

