---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-20 05:55:29 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (5 unique values: 81-88 cores)</summary>

```
1792489848 81
1792489853 81
1792489858 83
1792489863 83
1792489868 83
1792489873 85
1792489878 85
1792489883 85
1792489888 85
1792489893 85
1792489899 85
1792489904 85
1792489909 85
1792489914 85
1792489919 85
1792489924 85
1792489929 85
1792489934 85
1792489939 85
1792489944 85
```
</details>

---

