---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 04:34:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 11 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 971 |
| Sample Rate | 16.18/sec |
| Health Score | 1011% |
| Threads | 9 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789719888 43
1789719893 48
1789719898 48
1789719903 48
1789719908 48
1789719913 48
1789719918 48
1789719923 48
1789719928 48
1789719933 48
1789719938 48
1789719943 48
1789719948 48
1789719953 48
1789719958 48
1789719963 48
1789719968 48
1789719973 48
1789719978 48
1789719983 48
```
</details>

---

