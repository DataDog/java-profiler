---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-06 16:43:54 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 10 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 160 |
| Sample Rate | 2.67/sec |
| Health Score | 167% |
| Threads | 12 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 24-36 cores)</summary>

```
1794001164 24
1794001169 24
1794001174 24
1794001179 24
1794001184 24
1794001189 24
1794001194 24
1794001199 24
1794001204 24
1794001209 24
1794001214 24
1794001219 24
1794001224 24
1794001229 24
1794001234 24
1794001239 24
1794001244 24
1794001249 24
1794001254 24
1794001259 24
```
</details>

---

