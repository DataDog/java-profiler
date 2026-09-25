---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-25 06:35:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 871 |
| Sample Rate | 14.52/sec |
| Health Score | 907% |
| Threads | 9 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (3 unique values: 56-76 cores)</summary>

```
1790332143 66
1790332148 66
1790332153 66
1790332158 66
1790332163 66
1790332168 66
1790332173 66
1790332178 66
1790332183 66
1790332188 66
1790332193 66
1790332198 66
1790332203 76
1790332208 76
1790332213 76
1790332218 76
1790332224 76
1790332229 76
1790332234 76
1790332239 76
```
</details>

---

