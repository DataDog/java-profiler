---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-22 13:05:51 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 311 |
| Sample Rate | 5.18/sec |
| Health Score | 324% |
| Threads | 12 |
| Allocations | 146 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 13 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1787418113 34
1787418118 34
1787418123 34
1787418128 34
1787418133 34
1787418138 34
1787418143 34
1787418148 34
1787418153 34
1787418158 34
1787418163 29
1787418168 29
1787418173 29
1787418178 29
1787418183 29
1787418188 29
1787418193 29
1787418198 29
1787418203 29
1787418208 29
```
</details>

---

