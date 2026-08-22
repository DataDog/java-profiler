---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-22 13:05:51 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 141 |
| Sample Rate | 2.35/sec |
| Health Score | 147% |
| Threads | 10 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (2 unique values: 13-18 cores)</summary>

```
1787418123 18
1787418128 18
1787418133 18
1787418138 18
1787418143 18
1787418148 18
1787418153 18
1787418158 18
1787418163 18
1787418168 18
1787418173 18
1787418178 18
1787418183 18
1787418188 18
1787418193 18
1787418198 18
1787418203 18
1787418208 18
1787418213 18
1787418218 18
```
</details>

---

