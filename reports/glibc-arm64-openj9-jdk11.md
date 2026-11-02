---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 11:02:22 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 274 |
| Sample Rate | 4.57/sec |
| Health Score | 286% |
| Threads | 13 |
| Allocations | 95 |

<details>
<summary>CPU Timeline (4 unique values: 46-59 cores)</summary>

```
1793635047 46
1793635052 46
1793635057 46
1793635062 46
1793635067 46
1793635072 46
1793635077 46
1793635082 46
1793635087 46
1793635092 46
1793635097 59
1793635102 59
1793635107 48
1793635112 48
1793635117 48
1793635122 48
1793635127 53
1793635132 53
1793635137 53
1793635142 53
```
</details>

---

