---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-16 07:30:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 14 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1789557842 33
1789557847 64
1789557852 64
1789557857 64
1789557862 64
1789557867 64
1789557872 64
1789557877 64
1789557882 64
1789557887 64
1789557892 64
1789557897 64
1789557902 64
1789557907 64
1789557912 64
1789557917 64
1789557922 64
1789557927 64
1789557932 64
1789557937 64
```
</details>

---

