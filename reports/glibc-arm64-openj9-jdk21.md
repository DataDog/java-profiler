---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-21 05:49:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 266 |
| Sample Rate | 4.43/sec |
| Health Score | 277% |
| Threads | 11 |
| Allocations | 160 |

<details>
<summary>CPU Timeline (2 unique values: 18-23 cores)</summary>

```
1789983893 23
1789983898 23
1789983903 23
1789983908 23
1789983913 23
1789983918 18
1789983923 18
1789983928 18
1789983933 18
1789983938 18
1789983943 18
1789983948 18
1789983953 18
1789983958 18
1789983963 18
1789983968 23
1789983973 23
1789983978 23
1789983983 23
1789983988 23
```
</details>

---

