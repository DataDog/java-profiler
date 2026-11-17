---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 10:58:03 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 78-82 cores)</summary>

```
1794930722 82
1794930727 80
1794930732 80
1794930737 80
1794930742 80
1794930747 80
1794930752 82
1794930757 82
1794930762 82
1794930767 82
1794930772 82
1794930777 82
1794930782 82
1794930787 82
1794930792 82
1794930797 80
1794930802 80
1794930807 80
1794930812 80
1794930817 78
```
</details>

---

