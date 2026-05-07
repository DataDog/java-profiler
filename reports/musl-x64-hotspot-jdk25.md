---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 12:41:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 853 |
| Sample Rate | 14.22/sec |
| Health Score | 889% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (3 unique values: 40-55 cores)</summary>

```
1778171843 40
1778171848 40
1778171853 40
1778171858 40
1778171863 40
1778171868 40
1778171873 40
1778171878 50
1778171883 50
1778171888 50
1778171893 50
1778171898 50
1778171903 50
1778171908 50
1778171913 50
1778171918 50
1778171923 50
1778171928 55
1778171933 55
1778171938 55
```
</details>

---

