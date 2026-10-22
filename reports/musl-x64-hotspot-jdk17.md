---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 12:40:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 10 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 12 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 80-90 cores)</summary>

```
1792686847 88
1792686852 88
1792686857 88
1792686862 88
1792686867 88
1792686872 88
1792686877 88
1792686882 90
1792686887 90
1792686892 90
1792686897 90
1792686902 90
1792686907 90
1792686912 90
1792686917 90
1792686922 90
1792686927 90
1792686932 90
1792686937 90
1792686942 90
```
</details>

---

