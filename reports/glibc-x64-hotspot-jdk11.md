---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 12:39:24 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (3 unique values: 54-96 cores)</summary>

```
1792686783 96
1792686788 96
1792686793 96
1792686798 96
1792686803 96
1792686808 96
1792686813 96
1792686818 96
1792686823 96
1792686828 96
1792686833 96
1792686838 96
1792686843 96
1792686848 96
1792686853 96
1792686858 94
1792686863 94
1792686868 94
1792686873 94
1792686878 94
```
</details>

---

