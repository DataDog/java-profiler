---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-25 11:03:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 866 |
| Sample Rate | 14.43/sec |
| Health Score | 902% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787669859 64
1787669864 64
1787669869 64
1787669874 64
1787669879 64
1787669884 64
1787669889 64
1787669894 64
1787669899 64
1787669904 64
1787669909 64
1787669914 64
1787669919 64
1787669924 64
1787669929 64
1787669934 64
1787669939 64
1787669944 64
1787669949 64
1787669954 64
```
</details>

---

