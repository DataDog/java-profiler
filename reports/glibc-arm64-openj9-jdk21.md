---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 11:32:46 EST

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
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 12 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795192147 50
1795192152 50
1795192157 50
1795192162 50
1795192167 50
1795192172 50
1795192177 50
1795192182 50
1795192187 50
1795192192 50
1795192197 50
1795192202 50
1795192207 50
1795192212 50
1795192217 50
1795192222 50
1795192227 50
1795192232 50
1795192237 50
1795192242 50
```
</details>

---

