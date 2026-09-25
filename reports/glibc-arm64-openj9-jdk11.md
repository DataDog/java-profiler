---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-25 06:34:08 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 8 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 15 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790332069 50
1790332074 50
1790332079 50
1790332084 50
1790332089 50
1790332094 50
1790332099 50
1790332104 50
1790332109 50
1790332114 50
1790332119 50
1790332124 50
1790332129 50
1790332134 50
1790332139 50
1790332144 50
1790332149 50
1790332154 50
1790332159 50
1790332164 50
```
</details>

---

