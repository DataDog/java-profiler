---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 12:40:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
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
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792686832 32
1792686837 32
1792686842 32
1792686847 32
1792686852 32
1792686857 32
1792686862 32
1792686867 32
1792686872 32
1792686877 32
1792686882 32
1792686887 32
1792686892 30
1792686897 30
1792686902 30
1792686907 30
1792686912 30
1792686917 30
1792686922 30
1792686927 30
```
</details>

---

