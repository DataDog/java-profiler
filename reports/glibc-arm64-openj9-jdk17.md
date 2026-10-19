---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-19 05:04:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 13 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (3 unique values: 44-54 cores)</summary>

```
1792400092 54
1792400097 54
1792400102 54
1792400107 54
1792400112 49
1792400117 49
1792400122 49
1792400127 49
1792400132 49
1792400137 49
1792400142 49
1792400147 49
1792400152 49
1792400157 49
1792400162 49
1792400167 49
1792400172 44
1792400177 44
1792400182 44
1792400187 44
```
</details>

---

