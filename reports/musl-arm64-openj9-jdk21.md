---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-18 10:31:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 12 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 241 |
| Sample Rate | 4.02/sec |
| Health Score | 251% |
| Threads | 15 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1787063112 62
1787063117 62
1787063122 62
1787063127 64
1787063132 64
1787063137 64
1787063142 64
1787063147 64
1787063152 64
1787063157 64
1787063162 64
1787063167 64
1787063172 64
1787063177 64
1787063182 64
1787063187 64
1787063192 64
1787063197 64
1787063202 64
1787063207 64
```
</details>

---

