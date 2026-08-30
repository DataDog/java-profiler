---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-30 05:49:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 769 |
| Sample Rate | 12.82/sec |
| Health Score | 801% |
| Threads | 9 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1788083092 32
1788083097 32
1788083102 32
1788083107 32
1788083112 32
1788083117 32
1788083122 32
1788083127 32
1788083132 32
1788083137 32
1788083142 32
1788083147 32
1788083152 32
1788083157 32
1788083162 32
1788083167 32
1788083172 32
1788083177 32
1788083182 32
1788083187 32
```
</details>

---

