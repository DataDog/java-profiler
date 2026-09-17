---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 10:30:04 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 263 |
| Sample Rate | 4.38/sec |
| Health Score | 274% |
| Threads | 12 |
| Allocations | 119 |

<details>
<summary>CPU Timeline (4 unique values: 40-45 cores)</summary>

```
1789655062 45
1789655067 45
1789655072 40
1789655077 40
1789655082 40
1789655087 40
1789655092 40
1789655097 42
1789655102 42
1789655107 42
1789655112 42
1789655117 42
1789655122 42
1789655127 43
1789655132 43
1789655137 40
1789655142 40
1789655147 40
1789655152 40
1789655157 40
```
</details>

---

