---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-18 07:49:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 308 |
| Sample Rate | 5.13/sec |
| Health Score | 321% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 346 |
| Sample Rate | 5.77/sec |
| Health Score | 361% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 11-32 cores)</summary>

```
1789731793 32
1789731798 32
1789731803 32
1789731808 32
1789731813 32
1789731818 32
1789731823 11
1789731828 11
1789731833 11
1789731838 11
1789731843 11
1789731848 11
1789731853 11
1789731858 11
1789731863 11
1789731868 11
1789731873 11
1789731878 11
1789731883 11
1789731888 11
```
</details>

---

