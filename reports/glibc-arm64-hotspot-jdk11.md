---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 15:22:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 11 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 47-51 cores)</summary>

```
1794428193 47
1794428198 47
1794428203 47
1794428208 47
1794428213 47
1794428218 47
1794428223 47
1794428228 47
1794428233 47
1794428238 47
1794428243 47
1794428248 47
1794428253 47
1794428258 47
1794428263 47
1794428268 47
1794428273 47
1794428278 47
1794428283 51
1794428288 51
```
</details>

---

