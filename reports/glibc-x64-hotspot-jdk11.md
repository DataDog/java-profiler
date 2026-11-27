---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 08:43:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 6 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (3 unique values: 38-61 cores)</summary>

```
1795786668 40
1795786673 40
1795786678 40
1795786683 40
1795786688 61
1795786693 61
1795786698 38
1795786703 38
1795786708 38
1795786713 38
1795786718 38
1795786723 38
1795786728 38
1795786733 38
1795786738 38
1795786743 38
1795786748 38
1795786753 38
1795786758 38
1795786763 38
```
</details>

---

