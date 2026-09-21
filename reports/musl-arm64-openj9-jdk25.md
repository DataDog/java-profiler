---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 05:49:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 11 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 44-48 cores)</summary>

```
1789983803 44
1789983808 44
1789983813 44
1789983818 44
1789983823 44
1789983828 44
1789983833 44
1789983838 44
1789983843 44
1789983848 44
1789983853 44
1789983858 48
1789983863 48
1789983868 48
1789983873 48
1789983878 48
1789983883 48
1789983888 48
1789983893 48
1789983898 48
```
</details>

---

