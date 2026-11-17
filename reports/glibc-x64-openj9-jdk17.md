---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 10:58:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794930722 32
1794930727 32
1794930732 32
1794930737 32
1794930742 32
1794930747 32
1794930752 32
1794930757 32
1794930762 32
1794930767 32
1794930772 32
1794930777 32
1794930782 32
1794930787 32
1794930792 30
1794930797 30
1794930802 30
1794930807 30
1794930812 30
1794930817 30
```
</details>

---

