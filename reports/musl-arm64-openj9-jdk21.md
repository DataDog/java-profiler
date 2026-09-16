---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-16 12:11:38 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 142 |
| Sample Rate | 2.37/sec |
| Health Score | 148% |
| Threads | 10 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 258 |
| Sample Rate | 4.30/sec |
| Health Score | 269% |
| Threads | 16 |
| Allocations | 131 |

<details>
<summary>CPU Timeline (2 unique values: 25-30 cores)</summary>

```
1789574793 30
1789574798 30
1789574803 30
1789574808 30
1789574813 30
1789574818 30
1789574823 30
1789574828 30
1789574833 30
1789574838 30
1789574843 30
1789574848 25
1789574853 25
1789574858 25
1789574863 25
1789574868 25
1789574873 25
1789574878 25
1789574883 25
1789574888 25
```
</details>

---

