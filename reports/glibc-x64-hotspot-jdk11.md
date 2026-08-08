---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-08 00:56:58 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 8 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1786164803 44
1786164808 44
1786164813 44
1786164818 44
1786164823 44
1786164828 44
1786164833 44
1786164838 44
1786164843 44
1786164848 48
1786164853 48
1786164858 48
1786164863 48
1786164868 48
1786164873 48
1786164878 48
1786164883 48
1786164888 48
1786164893 48
1786164898 48
```
</details>

---

