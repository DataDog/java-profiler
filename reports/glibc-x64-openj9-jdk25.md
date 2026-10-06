---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-06 06:41:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 22-24 cores)</summary>

```
1791282924 22
1791282929 22
1791282934 22
1791282939 22
1791282944 22
1791282949 24
1791282954 24
1791282959 24
1791282964 24
1791282969 24
1791282974 24
1791282979 24
1791282984 24
1791282989 24
1791282994 24
1791282999 24
1791283004 24
1791283009 24
1791283014 24
1791283019 24
```
</details>

---

