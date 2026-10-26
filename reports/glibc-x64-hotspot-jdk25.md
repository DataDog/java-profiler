---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-26 08:33:31 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 409 |
| Sample Rate | 6.82/sec |
| Health Score | 426% |
| Threads | 10 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 88-90 cores)</summary>

```
1793017813 88
1793017818 88
1793017823 88
1793017828 88
1793017833 88
1793017838 88
1793017843 88
1793017848 90
1793017853 90
1793017858 90
1793017863 90
1793017868 88
1793017873 88
1793017878 88
1793017883 88
1793017888 88
1793017893 88
1793017898 88
1793017903 88
1793017908 88
```
</details>

---

