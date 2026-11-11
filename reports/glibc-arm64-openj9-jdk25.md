---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 12:34:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 12 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (4 unique values: 13-16 cores)</summary>

```
1794418113 16
1794418118 16
1794418123 16
1794418128 16
1794418133 16
1794418138 14
1794418143 14
1794418148 14
1794418153 14
1794418158 14
1794418163 14
1794418168 13
1794418173 13
1794418178 13
1794418183 13
1794418188 13
1794418193 13
1794418198 15
1794418203 15
1794418208 13
```
</details>

---

