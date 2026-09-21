---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-21 04:44:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 9 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (3 unique values: 20-24 cores)</summary>

```
1789979837 20
1789979842 20
1789979847 20
1789979852 20
1789979857 22
1789979863 22
1789979868 24
1789979873 24
1789979878 24
1789979883 24
1789979888 24
1789979893 24
1789979898 22
1789979903 22
1789979908 22
1789979913 22
1789979918 22
1789979923 22
1789979928 22
1789979933 22
```
</details>

---

