---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 08:20:14 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 12 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794403029 32
1794403034 32
1794403039 32
1794403044 32
1794403049 32
1794403054 32
1794403059 32
1794403064 32
1794403069 32
1794403074 32
1794403079 32
1794403084 32
1794403089 32
1794403094 32
1794403099 32
1794403104 32
1794403109 32
1794403114 32
1794403119 32
1794403124 32
```
</details>

---

