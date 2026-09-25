---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-25 06:34:09 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 234 |
| Sample Rate | 3.90/sec |
| Health Score | 244% |
| Threads | 14 |
| Allocations | 152 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790332108 50
1790332113 50
1790332118 50
1790332123 50
1790332128 50
1790332133 50
1790332138 50
1790332143 50
1790332148 50
1790332153 50
1790332158 50
1790332163 50
1790332168 50
1790332173 50
1790332178 50
1790332183 50
1790332188 50
1790332193 50
1790332198 50
1790332203 50
```
</details>

---

