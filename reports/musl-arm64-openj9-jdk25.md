---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-22 13:05:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 10 |
| Allocations | 113 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1787418102 48
1787418107 48
1787418112 48
1787418117 48
1787418122 48
1787418127 48
1787418132 48
1787418137 48
1787418142 48
1787418147 48
1787418152 48
1787418157 48
1787418162 48
1787418167 48
1787418172 48
1787418177 48
1787418182 48
1787418187 48
1787418192 48
1787418197 48
```
</details>

---

