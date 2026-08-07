---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-07 13:06:41 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 140 |
| Sample Rate | 2.33/sec |
| Health Score | 146% |
| Threads | 9 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 245 |
| Sample Rate | 4.08/sec |
| Health Score | 255% |
| Threads | 9 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1786122112 51
1786122117 51
1786122122 51
1786122127 51
1786122132 64
1786122137 64
1786122142 64
1786122147 64
1786122152 64
1786122157 64
1786122162 64
1786122167 64
1786122172 64
1786122177 64
1786122182 64
1786122187 64
1786122192 64
1786122197 64
1786122202 64
1786122207 64
```
</details>

---

